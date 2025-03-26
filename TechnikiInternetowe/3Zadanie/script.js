let rows = 2;
let columns = 5;

const plants = new Array(rows).fill().map(() => new Array(columns));

for(let i = 0; i < rows; i++){

	for(let j = 0; j < columns; j++){

		plants[i][j] = "None";

	}

}

function spawnSunflower(){
    
    console.log(document.getElementById("rowIndex").value);
    console.log(document.getElementById("columnIndex").value);
    
    row = document.getElementById("rowIndex").value;
    column = document.getElementById("columnIndex").value;

    if (plants[row-1][column-1] == "None") {

        document.getElementById("row" + row).querySelector("#column" + column + "plant").innerHTML = '<img src="assets/sunflower.png" width="128" height="128" alt="Obraz przedtawiający słonecznik">'; 
      
        plants[row-1][column-1] = "Sunflower"

        console.log("Sunflower spawned!");
    
    }

}

function spawnPea(){
    
    console.log(document.getElementById("rowIndex").value);
    console.log(document.getElementById("columnIndex").value);
    
    row = document.getElementById("rowIndex").value;
    column = document.getElementById("columnIndex").value;

    if (plants[row-1][column-1] == "None") {

        document.getElementById("row" + row).querySelector("#column" + column + "plant").innerHTML = '<img src="assets/pea.png" width="128" height="128" alt="Obraz przedtawiający groszek">'; 
      
        plants[row-1][column-1] = "Pea"

        console.log("Pea spawned!");
    
    }

}

function spawnGarlic(){
    
    console.log(document.getElementById("rowIndex").value);
    console.log(document.getElementById("columnIndex").value);
    
    row = document.getElementById("rowIndex").value;
    column = document.getElementById("columnIndex").value;

    if (plants[row-1][column-1] == "None") {

        document.getElementById("row" + row).querySelector("#column" + column + "plant").innerHTML = '<img src="assets/garlic.png" width="128" height="128" alt="Obraz przedtawiający czosnek">'; 
      
        plants[row-1][column-1] = "Garlic"

        console.log("Garlic spawned!");
    
    }

}

function removePlant(){
    
    console.log(document.getElementById("rowIndex").value);
    console.log(document.getElementById("columnIndex").value);
    
    row = document.getElementById("rowIndex").value;
    column = document.getElementById("columnIndex").value;

    if (plants[row-1][column-1] != "None") {

        document.getElementById("row" + row).querySelector("#column" + column + "plant").innerHTML = ""; 
      
        plants[row-1][column-1] = "None"

        console.log("Plant removed!");
    
    }

}

