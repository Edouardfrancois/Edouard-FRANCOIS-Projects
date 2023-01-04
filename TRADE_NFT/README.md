# How to use EION's NFT web app

## 1) **Prerequistes**

For use EION's NFT web app you must have a [METAMASK](https://metamask.io/) account and its extension browser that you can download [here](https://metamask.io/download/).


## 2) **Run the app**

Go in the EION_NFT/web/back and start the server with :
```
$ npm start
```

if the console print "*Go to localhost:3000* EION NFT web app is running."

## 3) **Use EION NFT WEB APP**

### **Minte a NFT**
Once the app is running, go to [localhost:3000]()

Now you have to answer the form. 

Normally your address is automatically filled thanks to Metamask extension.

Once the form is answered, click on the yellow button : "Create NFT".

The Metamask extension ask you to confirm the transaction, you have to click on "Confirm" button.

Then wait few seconds and the information of the NFT created will be displayed.

Congratulation, your NFT is minted.

### **Add your NFT to Metamask**

You cannot view your NFT on [METAMASK](https://metamask.io/) extension.

So you have to dowload the mobile app.

Once connected to your Metamask account with the mobile app

Go on "NFT" section and click on "Importer des NFT",

Then enter the Eion's contract adress :
```
0xC8C188948c916cd91f2A99931CAc99D6EbDbF5ee
```

and the NFT id that you can find by clicking on the "**See on Etherscan**" button on [http://localhost:3000/]() after the NFT minte.

Now you can view your NFT on MetaMask mobile app. 


### Transphere your NFT

Go to [http://localhost:3000/transphere](http://localhost:3000/transphere)

Indicate the public key of the futur owner and the ID of the NFT you want to transphere.

Then click on the "TRANSPHERE NFT" button. And accept the transaction on the Metamask window.

### Sell your NFT

go to [http://localhost:3000/marketplace](http://localhost:3000/marketplace)

Indicate the price that you want to send and the id of the NFT.

The click on the "Add to marketplace" button and accept the transaction on the Metamask window.

### View NFT on the marketplace

go to [http://localhost:3000/shop](http://localhost:3000/shop)

Then click on the "Update Shop" button



