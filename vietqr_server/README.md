## Quick start

Before run, install dependencies

```bash
npm i package.json
```

Run below command to start server

```bash
npm run test
```

## API References

### GET `/test/:amount`

A simple api to test. It will be generating a QR to my bank account

#### Params

| Param  | Description     |
| ------ | --------------- |
| amount | amount of money |

#### Return

Return a 64x64 QR as bitmap array string separated by comma

### GET `/qr/:bank/:account/:amount`

Generating transaction QRCode

#### Params

| Param   | Description                                                    |
| ------- | -------------------------------------------------------------- |
| bank    | bank short name ([See full list](https://api.vietqr.io/v2/banks)) |
| account | bank account                                                   |
| amount  | amount of money                                                |

#### Queries

| Param   | Description                                                                                                           |
| ------- | --------------------------------------------------------------------------------------------------------------------- |
| content | content of transaction                                                                                                |
| size    | size of QR as pixel.**Default is 64**                                                                           |
| ret     | Return format.`<br>` **Image**: Default. return QR image`<br>` **bitmap**: return bitmap array string |

#### Return

Return format based on `ret` param.
