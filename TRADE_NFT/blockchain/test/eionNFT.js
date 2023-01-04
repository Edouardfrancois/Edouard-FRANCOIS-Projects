const { ethers } = require("hardhat")
const { expect } = require("chai");

describe("Ben BK vidéo", function() {
    before(async function() {
        [this.owner, this.addr1, this.addr2] = await ethers.getSigners();
    })
})

describe("Contract : eionNFT", function () {
    it("Methode : mintNFT", async function () {
        const [owner] = await ethers.getSigners();

        const eionNFT = await ethers.getContractFactory("NFTMinterEion");

        const contract = await eionNFT.deploy();

        const balanceBefore = await contract.balanceOf(owner.address);
        expect(balanceBefore).to.equal(0);
        const resMint = await contract.mintNFT(owner.address, "");
        const balanceAfter = await contract.balanceOf(owner.address);
        expect(balanceAfter).to.equal(1);
    });
});






// describe("Contract : NftTrader", function () {
//     it("Methode : addListing", async function () {
//         const owner = await ethers.getSigners();

//         const artifacts_eionNFT = await ethers.getContractFactory("NFTMinterEion");
//         const contract_eionNFT = await artifacts_eionNFT.deploy();

//         const artifacts_NftTrader = await ethers.getContractFactory("NftTrader");
//         const contract_NftTrader = await artifacts_NftTrader.deploy();
        
//         await contract_eionNFT.mintNFT(owner[0].address, "");
//         // try:
//         // await contract_NftTrader.addListing(10, owner.address, 1);
//         const secondAddressSigner = await ethers.getSigner(owner[1].address)
//         await contract_NftTrader.connect(secondAddressSigner).addListing(10, owner[0].address, 1)
//         // catch(err)
//     });
// });
