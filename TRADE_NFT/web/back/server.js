// Creates an Express application. The express() function is a top-level function exported by the express module.
import express from "express";
// The 'path' module provides helpers for manipulating filesystem paths
import path from 'path'
// Import the NFTStorage class and File constructor from the 'nft.storage' package
import { NFTStorage, File } from 'nft.storage'
// The 'mime' npm package helps us set the correct file type on our File objects
import mime from 'mime'
// The 'fs' builtin module on Node.js provides access to the file system
import fs from 'fs'
// Zero-dependency module that loads environment variables from a .env file into process.env
import dotenv from 'dotenv'
// The JSON of a contract’s ABI gives various functions and/or events descriptions of the smart contract.
import contractABI from '../../blockchain/contract-abi.json' assert {type: 'json'};
// The path.dirname() method returns the directories of a file path.
import { dirname } from 'path';
// This function ensures the correct decodings of percent-encoded characters as well as ensuring a cross-platform valid absolute path string.
import { fileURLToPath } from 'url';
// Creates an Alchemy instance to interact with ethereum blockchain (or testnet blockchain)
import { createAlchemyWeb3 } from '@alch/alchemy-web3'

// Loads .env file contents into process.env
dotenv.config()

// Assigns const to env variables previously stored in provess.env
const alchemyKey = process.env.ALCHEMY_KEY;
const contractAddress = process.env.CONTRACT_ADDRESS;
const nftstorage_key = process.env.NFTSTORAGE_KEY;

// Create the client and put the API key to interact with blockchain
const web3 = createAlchemyWeb3(alchemyKey);
// Creates an Express application. The express() function is a top-level function exported by the express module.
const app = express();
// Use express.Router class to create routes managers. Router is a middleware called mini-app.
const router = express.Router();
// define environment variable that tells you the absolute path of the directory containing the currently executing file.
const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);

// A built-in middleware function which parses incoming requests with urlencoded and JSON payloads and is based on body-parser.
app.use(express.urlencoded());
app.use(express.json());


// Routes HTTP POST requests to the specified path with the specified callback functions.
app.post('/upload_ipfs', (req, res) => {
  console.log("upload_ipfs::::::::::::::::::::::::::::::::::::::::::::::::::")
  // The purpose of "use strict" is to indicate that the code should be executed in "strict mode". With strict mode, you can not, for example, use undeclared variables.
  "use strict";

  // Log in the console the request body (img_name && img_desc && img_path && user_address)
  console.log('req::'+ JSON.stringify(req.body));

  /**
  * A helper to read a file from a location on disk and return a File object.
  * @param {string} filePath the path to a file to store
  * @returns {File} a File object containing the file content
  */
  async function fileFromPath(filePath) {

    // This method read the entire file into buffer.
    const content = await fs.promises.readFile(filePath)
    // Get the type of the file to be stored
    const type = mime.getType(filePath)
  
    // Create and return an object File containing the content, the path and the file type
    return new File([content], path.basename(filePath), { type })
  }

  /**
  * Reads an image file from `imagePath` and stores an NFT with the given name and description.
  * @param {string} file_path the path to an image file
  * @param {string} name a name for the NFT
  * @param {string} description a text description for the NFT
  * @param {string} author an author for the NFT
  * @returns {Token} an object containing the image data (File, desc and name) (IPFS link can be obtained with {token}.url)
  */
  async function storeNFT(name, description, file_path, author) {
    
    // Log in the console the request body (img_name && img_desc && img_path && user_address)
    console.log('Look what is there ....' + JSON.stringify(req.body) +'      ');

    // Error management if the file_path doesn't exist
    if (!file_path || file_path == '') {
      console.log('file_path:: Not defined');
    } else {
      // Create a new NFTStorage client using API key previsouly obtained with dotenv
      const nftstorage = new NFTStorage({ token: nftstorage_key, endpoint: new URL('https://api.nft.storage/')})
      // Load the file from disk
      const image = await fileFromPath(file_path);
      console.log(author);
      // The JavaScript client's store(token) method takes a single token argument, which contains the metadata for your NFT as a JavaScript object.
      return nftstorage.store({
        name,
        description,
        image,
        "properties" : {
          "origins" : {
            "http" : "https://www.eion.io",
          },
          "author" : author,
        }
      })
    }//if-else{}
          
  }

  /**
  * Create an object with the transaction parameters needed to the wallet signature
  * @param {string} user_address the adress of the future nft's owner
  * @param {string} tokenURI IPFS link of the previous image stored
  * @returns {transactionParameters} an object containing the parameters of the transaction (smart contract address, owner wallet address, smart contract description and tokenURI of the image)
  */
  function setParams(user_address, tokenURI, royalties) {

    // Creates a new contract instance with all its methods and events defined in its json interface object (contractABI).
    const contract = new web3.eth.Contract(contractABI, contractAddress);
    console.log("royalty before call MINTNFT : " + royalties)
    // Creates an transaction object with all the data needed for the wallet signature
    const transactionParameters = {
      to: contractAddress, // Required except during contract publications.
      from: user_address, // must match user's active address.
      'data': contract.methods.mintNFT(user_address, tokenURI, royalties).encodeABI() //make call to NFT smart contract
    };
    return (transactionParameters);
  }

  /**
  * Main async function with all the steps inside
  * @param {Request} req The request object obtained when the user submit the form (made of the name of the image, its description, its path and the user wallet address)
  */
  async function storeAndParams (req) {

    // Assigns the req.body to const variables
    const name        = req.body.img_name;
    const description = req.body.img_desc;
    const file_path   = req.body.img_path || '';
    const user_address = req.body.user_address;
    const author = req.body.author;
    const royalties = req.body.royalty;
    
    console.log(req.body.author)

    // Call storeNFT async function to upload image submitted by the user on the IPFS and get the TokenURI for the NFT creation
    const tokenURI = await storeNFT(name, description, file_path, author);
    const token_url   = tokenURI.url;
    const tokenHTML = token_url.replace("ipfs://", "https://ipfs.io/ipfs/");
    console.log('       tokenHTML::    ' + tokenHTML + "\n");
    console.log(tokenURI.url) 
    const img_json = '';

    // Prepare the parameters for the wallet signature
    const transParams = setParams(user_address, tokenURI.url, royalties);
    // Send the transactionParameters through a JSON
    res.json({ transactionParameters: transParams, contractAddress: contractAddress, tokenURI: tokenURI.url, 'errror' : '0', 'imageParams' : img_json});
  }

  // Call the main function
  storeAndParams(req).catch(err => {

  // Print the error in this case
  console.error(err)
  });
});


app.post('/transphere/tst', (req, res) => {
  console.log("transphere is runing :\n");
  
  console.log("id : " + req.body.id);
  console.log("from : " + req.body.from);
  console.log("to : " + req.body.to);
  const contract = new web3.eth.Contract(contractABI, contractAddress);

  const Params = {
    to: process.env.CONTRACT_ADDRESS,
    from: req.body.from, // must match user's active address.
    // contract.methods['safeTransferFrom(address,address,uint256)'](sender, reciver, nftId).send({ from: sender })
    'data': contract.methods['safeTransferFrom(address,address,uint256)'](req.body.from, req.body.to, req.body.id).encodeABI() //make call to NFT smart contract
  };
  console.log("transphere is finish");
  res.json({transactionParameters: Params, 'errror' : '0'});
  console.log("transphere is realy finish");
});

// View all the NFT on the listing
app.post('/listings', async (req, res) => {
  console.log("You are on listings");
  const contract = new web3.eth.Contract(contractABI, contractAddress);
  const max = await contract.methods._tokenIds().call();
  console.log(max);
  const listings = [];
  for(let i =1; i <= max;i++) {
    const listing = await contract.methods.listings(i).call();
    if(listing.seller === "0x0000000000000000000000000000000000000000") {
      console.log("NFT numero " + i + " is not listed")
    } else {
      console.log("ELSE ________________")
      let uri = await contract.methods.tokenURI(i).call();
      listings.push(uri)
    }
    console.log(listings)
  }
  res.json({'uri': listings})
});

// For put on listing an NFT
app.post('/marketplace/submit', async (req, res) => {
  console.log("respons of form add list :\n");
  
  console.log("id : " + req.body.tokenId);
  console.log("price : " + req.body.price);
  console.log("from : " + req.body.from);
  const contract = new web3.eth.Contract(contractABI, contractAddress);

  const Params = {
    to: process.env.CONTRACT_ADDRESS,
    from: req.body.from,
    data: contract.methods['addListing(uint256,uint256)'](req.body.price, req.body.tokenId).encodeABI()
  };
  console.log("listing[1]" + Params.data);
  res.json({transactionParameters: Params, 'errror' : '0'});
  console.log("listings is realy finish");
}); 


router.get('/',function(req, res) {
  "use strict";
  res.sendFile(path.join(__dirname+'/../front/index.html'));
})

router.get('/transphere',function(req, res) {
  "use strict";
  res.sendFile(path.join(__dirname+'/../front/transphere.html'));
})

router.get('/shop',function(req, res) {
  "use strict";
  res.sendFile(path.join(__dirname+'/../front/shop.html'));
})

router.get('/marketplace',function(req, res) {
  "use strict";
  res.sendFile(path.join(__dirname+'/../front/marketplace.html'));
})

// Add the router
app.use('/img', express.static('img'));
app.use('/', router);
app.listen(process.env.port || 3000);

// Log the port where we can access to the form
console.log('Go to localhost:3000');