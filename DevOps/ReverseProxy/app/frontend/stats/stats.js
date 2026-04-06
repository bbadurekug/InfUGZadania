async function pobierzDane() {
    try {
        const response = await fetch('/api/stats/');
        
        if (!response.ok) {
            throw new Error(`Błąd serwera: ${response.status}`);
        }

        const data = await response.json();

        console.log(data);

        return data;
    } catch (error) {
        console.error("Wystąpił błąd podczas pobierania:", error);
    }
}

async function odswierzDane() {
    const data = await pobierzDane();

    const numberOfProductsP = document.getElementById('number-of-products');

    numberOfProductsP.innerHTML = data;
}

odswierzDane();