let matrixRows = 3;
let matrixColumns = 6;

const matrix = new Array(matrixRows).fill().map(() => new Array(matrixColumns));

for(let i = 0; i < matrixRows; i++){

	for(let j = 0; j < matrixColumns; j++){

		matrix[i][j] = 1;

	}

}

function prepareEmptyMatrix(){
	
	let matrixString = "$\\begin{bmatrix}";

	for(let i = 0; i < matrixColumns; i++){
		
		for(let j = 0; j < matrixRows; j++){
			
			matrixString += matrix[j][i];

			if(j < matrixRows - 1) matrixString += "&";

		}

		matrixString += "\\\\";

	}
	
	matrixString += "\\end{bmatrix}$"

	return matrixString;

}

function updateMatrix(){

	document.getElementById("matrixInput").innerHTML = prepareEmptyMatrix(); 
	
//	MathJax.typeset();

}

updateMatrix();
