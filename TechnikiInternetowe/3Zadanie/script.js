let rows = 2;
let columns = 5;

const plants = new Array(rows).fill(new Array(columns));

for(let i = 0; i < rows; i++){

	for(let j = 0; j < 5; j++){

		plants[i][j] = "none";

	}

}

const spawnSunflower = ()=> console.log("Sunflower spawned");

function updatePlants(){

	console.log(plants);

	document.getElementById("row1plants").innerText = '<img src="sunflower.png">';

}

updatePlants();
