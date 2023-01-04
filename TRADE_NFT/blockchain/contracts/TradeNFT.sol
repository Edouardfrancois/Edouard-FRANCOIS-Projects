pragma solidity 0.8.17;

import "@openzeppelin/contracts/token/ERC1155/ERC1155.sol";
import "./eionNFT.sol";

contract NftTrader {

    struct Listing {
        uint256 price;
        address seller;
    }
    // address public tst;
    // uint public balance = 0;

    mapping(address => mapping(uint256 => Listing)) public listings;

    function addListing(uint256 price, address contractAddress, uint256 tokenId) public {
        NFTMinterEion nft = NFTMinterEion(contractAddress);
        require(nft.ownerOf(tokenId) == msg.sender, "NftTader: seller must own given nft");
    }
}