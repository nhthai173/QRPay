const Jimp = require("jimp")


/**
 * Read image from path and convert it to bitmap array string separated by comma
 * @param {string} imgPath image path to convert
 * @returns {string} bitmap array string separated by comma
 */
module.exports.convertToBMP = async function (imgPath) {
    if (!imgPath) {
        throw new Error('Image path is required');
    }
    const image = await Jimp.read(imgPath);
    image.grayscale();

    const bitmap = [];

    for (let y = 0; y < 64; y++) {
        let byte = 0;
        for (let x = 0; x < 64; x++) {
            const pixel = Jimp.intToRGBA(image.getPixelColor(x, y));
            const color = pixel.r > 128 ? 1 : 0;
            byte = (byte << 1) | color;
            if (x % 8 === 7) {
                bitmap.push(byte);
                byte = 0;
            }
        }
    }

    return bitmap.join(',');
}