const express = require('express');
const fs = require('fs');
const { convertToBMP } = require('./img-utils');
const { generateTransactionQRCode } = require('./qr-utils');

const SERVER_PORT = 3008;
const app = express();

app.get('/', async function (req, res) {
    res.status(200).send('Hello World');
})

// Test API with amount
// Example: http://localhost:3008/test/10000
app.get('/test/:amount', async function (req, res) {
    try {
        const amount = req.params.amount || 0;

        // Generate QR code
        const imgPath = generateTransactionQRCode({
            bank: 'vietcombank',
            account: 'nhthai',
            amount,
            size: 64
        });

        // Convert QR code to BMP
        const bitmap = await convertToBMP(imgPath);
        res.send(bitmap);
    } catch (err) {
        console.error('Error generating QRCode', err);
        res.status(500).send(err.message);
    }
});


// Generate QR code API
// Example: http://localhost:3008/qr/vietcombank/nhthai/10000?content=Test&size=64&ret=image
app.get('/qr/:bank/:account/:amount', async function (req, res) {
    const { bank, account, amount } = req.params || {};
    const { content, size, ret = 'image' } = req.query || {};
    
    if (!bank || !account) {
        res.status(400).send('Bank and account are required');
        return;
    }

    try {
        // Generate QR code
        if (ret === 'image') {
            const dataurl = await generateTransactionQRCode({
                bank,
                account,
                amount,
                content,
                size,
                type: 'DATAURL'
            });
            res.setHeader('Content-Type', 'image/png');
            res.send(Buffer.from(dataurl.split('base64,')[1], 'base64'));
        } else {
            const imgPath = await generateTransactionQRCode({
                bank,
                account,
                amount,
                content,
                size,
                type: 'file'
            });
            // Convert QR code to BMP
            const bitmap = await convertToBMP(imgPath);
            res.setHeader('Content-Type', 'text/plain');
            res.send(bitmap);
        }
    } catch (err) {
        console.error('Error generating QRCode', err);
        res.status(500).send(err.message);
    }

})


app.listen(SERVER_PORT, function () {
    console.log('Server is running on port', SERVER_PORT);
});