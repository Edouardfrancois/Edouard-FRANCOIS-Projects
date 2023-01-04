// 
//
/// -> This is the real EION's SMART CONTRACT
//
//

pragma solidity 0.8.17;
import "@openzeppelin/contracts/token/common/ERC2981.sol";
import "@openzeppelin/contracts/token/ERC721/extensions/ERC721URIStorage.sol";
import "@openzeppelin/contracts/utils/Counters.sol";
import "@openzeppelin/contracts/access/Ownable.sol";

contract NFT_EION is ERC721URIStorage, ERC2981 {
    using Counters for Counters.Counter;

    Counters.Counter public _tokenIds;

    constructor() public ERC721("NFT_EION", "NFT") {}

// variables for stock information about the sell
    struct Listing {
        uint256 price;
        address seller;
    }

    mapping(uint256 => Listing) public listings;
    mapping(address =>uint256) public balances;

    /**
     * @dev See {IERC165-supportsInterface}. It is mandatory to override this function from ERC2981
     */
    function supportsInterface(bytes4 interfaceId) public view virtual override(ERC721, ERC2981) returns (bool) {
        return super.supportsInterface(interfaceId);
    }

    function mintNFT(address recipient, string memory tokenURI, uint96 royaltiesPercentage) public returns (uint256) {
        require(royaltiesPercentage <= 100, "NFT_EION: royaltiesPercenntagen must be between 0 and 100");
        _tokenIds.increment();

        uint256 newItemId = _tokenIds.current();
        _mint(recipient, newItemId);
        _setTokenURI(newItemId, tokenURI);
        // feeNumerator is 3000 (royaltiesPercentage * 100) because _feeDenominator() = 10000, 
        // so saleprice * royaltiesPercentage * 100 / feeDenominator = royaltiesPercentage% of saleprice
        _setTokenRoyalty(newItemId, msg.sender, (royaltiesPercentage * 100));

        return newItemId;
    }

    function setTokenRoyalty(uint256 tokenId, uint96 royaltiesPercentage) public {
        (address author,) = royaltyInfo(tokenId, 0);
        require(author == msg.sender, "NFT_EION: only the owner of copyright can use this function");
        _setTokenRoyalty(tokenId, msg.sender, (royaltiesPercentage * 100));
    }

    function addListing(uint256 price, uint256 tokenId) public {
        require(ownerOf(tokenId) == msg.sender, "NFT_EION: seller must own given nft");
        //require(isApprovedForAll(msg.sender, address(this)), "contract must be approved");

        listings[tokenId] = Listing(price, msg.sender);
        //setApprovalForAll(address(this), tokenId);
        _approve(address(this), tokenId);
    }

    function purchase(uint256 tokenId) public payable {
        Listing memory sold_info = listings[tokenId];
        require(msg.value >= sold_info.price);

        (address owner_royalties, uint256 royaltyAmount) = royaltyInfo(tokenId, msg.value);
        balances[sold_info.seller] += (msg.value - royaltyAmount);
        balances[owner_royalties] += royaltyAmount;

        //test();
        _approve(msg.sender, tokenId);
        safeTransferFrom(sold_info.seller, msg.sender, tokenId, "");
    }

    function withdraw(address payable destAddress) public {
        destAddress.transfer(balances[msg.sender]);
        balances[msg.sender] = 0;
    }
}