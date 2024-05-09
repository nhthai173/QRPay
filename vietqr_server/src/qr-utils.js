const QR = require('qrcode');
const { QRPay, BanksObject } = require('vietnam-qr-pay');



/**
 * Generate transaction QR code
 * @param {Object} options 
 * @param {string} options.bank bank short name (ex: 'vietcombank', 'acb')
 * @param {string} options.account bank account number
 * @param {number} options.amount transaction amount
 * @param {string} options.content transaction content
 * @param {number} options.size QR code size
 * @param {string} options.imgPath image path to save QR code
 * @returns {string} image path of generated QR code
 */
module.exports.generateTransactionQRCode = function ({ bank, account, amount = 0, content = "", size = 64, imgPath = 'qr.png' } = {}) {
    if (!bank || !account) {
        throw new Error('Bank and account are required');
    }

    if (!BanksObject[bank]) {
        throw new Error('Bank not supported');
    }

    const qrPay = QRPay.initVietQR({
        bankBin: BanksObject[bank].bin,
        bankNumber: account,
        amount,
        purpose: content,
    })
    const qrData = qrPay.build()

    QR.toFile(imgPath, qrData, { errorCorrectionLevel: 'L', width: size, height: size, margin: 0 });
    return imgPath;
}