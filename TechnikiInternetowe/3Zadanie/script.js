let rows = 2;
let columns = 5;
let noPlants = 3;

const plantsToChoose = new Array(noPlants);

plantsToChoose[0] = "sunflower";
plantsToChoose[1] = "pea";
plantsToChoose[2] = "garlic";

const plants = new Array(rows).fill().map(() => new Array(columns));

for(let i = 0; i < rows; i++){

	for(let j = 0; j < columns; j++){

		plants[i][j] = ["none", 0];

	}

}

function getRandomPlant(){
    return plantsToChoose[Math.floor(Math.random() * noPlants)];
}

function isMoreSpace(){
    
    let oneNone = false;
        
    for(let i = 0; i < rows; i++){

	    for(let j = 0; j < columns; j++){

	    	if (plants[i][j][0] == "none") {
                
                oneNone = true;
                break;

            }

	    }

    }   

    return oneNone;

}

function updatePlant(row, column){

    document.getElementById("row" + row).querySelector("#column" + column + "plant").innerHTML = '<img src="assets/' +  plants[row-1][column-1][0] + '.png" style="scale: ' +  plants[row-1][column-1][1] + '%; bottom: ' + (-48 - (0.16 * plants[row-1][column-1][1])) + 'px" alt="' + plants[row-1][column-1][0] + '">'; 

}

function isFirstPlant(){

    let allNone = true;

    for(let i = 0; i < rows; i++){

	    for(let j = 0; j < columns; j++){

	    	if (plants[i][j][0] != "none") {
                
                allNone = false;
                break;

            }

	    }

    }   

    return allNone;

}

function spawnPlant(plant){
    
    if (isFirstPlant() == false){

        return;

    }

    console.log(document.getElementById("rowIndex").value);
    console.log(document.getElementById("columnIndex").value);
    
    row = document.getElementById("rowIndex").value;
    column = document.getElementById("columnIndex").value;

    if (plants[row-1][column-1][0] == "none") {
        
        plants[row-1][column-1][0] = plant;
        plants[row-1][column-1][1] = 10;

        updatePlant(row, column);        

        console.log(plant + " spawned!");
    
    }

}

function spawnPlantRandom(plant){
    
    if (isMoreSpace() == false) {
        
        return;
    }

    row = Math.floor(Math.random() * rows);
    column = Math.floor(Math.random() * columns);
    
    while (plants[row][column][0] != "none") {

        row = Math.floor(Math.random() * rows);
        column = Math.floor(Math.random() * columns);

    }

    plants[row][column][0] = plant;
    plants[row][column][1] = 10;

    updatePlant(row + 1, column + 1);        

    console.log(plant + " spawned!");
    
}

function waterPlant(){

    console.log(document.getElementById("rowIndex").value);
    console.log(document.getElementById("columnIndex").value);
    
    row = document.getElementById("rowIndex").value;
    column = document.getElementById("columnIndex").value;

    if(plants[row-1][column-1][1] >= 150) {
   
        document.getElementById("row" + row).querySelector("#column" + column + "plant").innerHTML = '<img src="assets/' +  plants[row-1][column-1][0] + '.png" style="scale: ' +  plants[row-1][column-1][1] + '%; bottom: ' + (-48 - (0.16 * plants[row-1][column-1][1])) + 'px; border-radius: 50%; background-color: rgba(255, 0, 0, 0.5)" alt="' + plants[row-1][column-1][0] + '">'; 

        return;

    }   

    if (plants[row-1][column-1][0] != "none") {
    
        plants[row-1][column-1][1] += 10;

        updatePlant(row, column); 

    }

}

function waterPlantAll(){

    for(let i = 0; i < rows; i++){

	    for(let j = 0; j < columns; j++){

            if(plants[i][j][1] >= 150) {
   
                document.getElementById("row" + (i + 1)).querySelector("#column" + (j + 1) + "plant").innerHTML = '<img src="assets/' +  plants[i][j][0] + '.png" style="scale: ' +  plants[i][j][1] + '%; bottom: ' + (-48 - (0.16 * plants[i][j][1])) + 'px; border-radius: 50%; background-color: rgba(255, 0, 0, 0.5)" alt="' + plants[i][j][0] + '">'; 

                continue;

            }   

	    	if (plants[i][j][0] != "none") {
                
                plants[i][j][1] += 10;
                updatePlant(i + 1, j + 1);

            }

	    }

    }   

}

function isLastLeft(row, column) {

    let lastLeft = true;

    for(let i = 0; i < rows; i++){

	    for(let j = 0; j < columns; j++){

	    	if (!(row == i && column == j) && plants[i][j][0] != "none") {
                
                lastLeft = false;
                break;

            }

	    }

    }

    return lastLeft;

}

function removePlant(){

    console.log(document.getElementById("rowIndex").value);
    console.log(document.getElementById("columnIndex").value);
    
    row = document.getElementById("rowIndex").value;
    column = document.getElementById("columnIndex").value;
    
    if (isLastLeft(row - 1, column - 1) == true) {

        plants[row-1][column-1][1] = 10;
        updatePlant(row, column);
        return;

    }

    if (plants[row-1][column-1][0] != "none") {
        
        plants[row-1][column-1][0] = "none";
        plants[row-1][column-1][1] += 0;

        document.getElementById("row" + row).querySelector("#column" + column + "plant").innerHTML = ''; 

    }

}

function healPlants(){

    for(let i = 0; i < rows; i++){

        for(let j = 0; j < columns; j++){

	    	if (plants[i][j][1] >= 150) {
                
                plants[i][j][1] = 10;
                updatePlant(i + 1, j + 1);

            }

	    }

    }   

}
