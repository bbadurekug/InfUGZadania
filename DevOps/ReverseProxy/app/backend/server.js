const express = require('express');
const app = express();
const PORT = process.env.PROT || 3000;

const items = ['item1', 'item2', 'item3'];

app.get('/items', (req, res) => {
    //definicja
});

app.post('/items', (req, res) => {
    //definicja
});

app.get('/stats', (req, res) => {
    //definicja
});

app.listen(PORT, () => {
    console.log(`Serwer nasłuchuje na porcie: ${PORT}`);
});