const express = require('express');
const os = require('os');
const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.json());

var items = ['item1', 'item2', 'item3'];

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

    res.status(201).json({
        message: "Produkty zostal pomyslnie dodany!",
        item: newItem
    });
});

app.get('/api/stats', (req, res) => {
    res.json({
        item_count: items.length,
        backend_id: os.hostname()
    });
});

app.listen(PORT, () => {
    console.log(`Serwer nasłuchuje na porcie: ${PORT}`);
});