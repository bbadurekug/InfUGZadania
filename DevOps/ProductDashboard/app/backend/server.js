const express = require('express');
const os = require('os');
const fs = require('fs');
const app = express();
const PORT = process.env.PORT || 3000;

const ITEMS_DATA_PATH = '/data/items.json';

app.use(express.json());

const instanceId = process.env.INSTANCE_ID || os.hostname();

let items = [];

if (fs.existsSync(ITEMS_DATA_PATH)) {
    items = JSON.parse(fs.readFileSync(ITEMS_DATA_PATH, 'utf8'));
} else {
    fs.writeFileSync(ITEMS_DATA_PATH, JSON.stringify(items));
}

app.get('/api/items', (req, res) => {
    res.json(items);
});

app.post('/api/items', (req, res) => {
    const newItem = req.body.item;

    if (typeof newItem !== 'string' || newItem.trim() === '') {
        res.status(400).json({
            message: "Produkt musi byc byc napisem!"
        });
    }

    items.push(newItem);
    fs.writeFileSync(ITEMS_DATA_PATH, JSON.stringify(items));

    res.status(201).json({
        message: "Produkty zostal pomyslnie dodany!",
        item: newItem
    });
});

app.get('/api/stats', (req, res) => {
    res.json({
        item_count: items.length,
        backend_id: instanceId
    });
});

app.get('/api/health', (req, res) => {
    res.json({
        status: "ok"
    });
});

app.listen(PORT, () => {
    console.log(`Serwer nasłuchuje na porcie: ${PORT}`);
});