const form = document.getElementById('product-form');
const productNameInput = document.getElementById('product-form-name');

form.addEventListener('submit', async (event) => {
    event.preventDefault();

    const productName = productNameInput.value.trim();

    const response = await dodajProdukt(productName);

    if (response.ok) {
        productNameInput.value = '';
    }
});

async function pobierzDane() {
    try {
        const response = await fetch('/api/items');
        
        if (!response.ok) {
            throw new Error(`Błąd serwera: ${response.status}`);
        }

        const data = await response.json();

        return data;
    } catch (error) {
        console.error("Wystąpił błąd podczas pobierania:", error);
    }
}

async function odswierzListe() {
    const lista = document.getElementById('product-list');

    const data = await pobierzDane();

    lista.innerHTML = '';

    if (!data) return;

    data.forEach(product => {
        const li = document.createElement('li');
            
        li.textContent = product;

        lista.appendChild(li);
    });
}

async function dodajProdukt(productName) {
    try {
        const response = await fetch('/api/items', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ item: productName })
        });

        if (!response.ok) {
            throw new Error(`Błąd serwera: ${response.status}`);
        } else {
            await odswierzListe();
            return response;
        }
    } catch (error) {
        console.error("Wystąpił błąd podczas dodawania produktu:", error);
    }
}

odswierzListe();