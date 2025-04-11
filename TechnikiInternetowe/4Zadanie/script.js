let matrixRows = 1;
let matrixColumns = 1;

matrix = new Array(matrixRows).fill().map(() => new Array(matrixColumns));

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

	document.getElementById("matrixCalculation").innerHTML += prepareEmptyMatrix() + '<br>'; 
    
    MathJax.typeset();

}

function buttonAction(){
    
    document.getElementById("matrixCalculation").innerHTML = '<button onclick="buttonAction()">Return</button><br><button id="calculationButton" onclick="calculate()">Calculate</button><br>';

    document.getElementById("matrixCalculation").style.display = "none";
    document.getElementById("menu").style.display = "none";
   
    matrixRows = document.querySelector('input[name="matrixSize"]:checked').value.split('x').map(Number)[0];
    matrixColumns = document.querySelector('input[name="matrixSize"]:checked').value.split('x').map(Number)[1];

    matrix = new Array(matrixRows).fill().map(() => new Array(matrixColumns));

    let inputMatrix = ""

    for(let i = 0; i < matrixRows; i++){
    
    	for(let j = 0; j < matrixColumns; j++){
    
    		inputMatrix += '<input type="text" id="' + j + i + '" value="' + (j + i) + '">';
    
    	}
    
    }
    
    document.getElementById("matrixInputGrid").style.gridTemplateColumns = "repeat(" + matrixColumns + ", 40px)";
    document.getElementById("matrixInputGrid").style.gridTemplateRows = "repeat(" + matrixRows + ", 40px)";
    
    document.getElementById("matrixInputGrid").innerHTML = inputMatrix;
    
    document.getElementById("matrixInput").style.display = "flex";

}

function buttonReturn(){
    
    document.getElementById("matrixInput").style.display = "none";

    document.getElementById("menu").style.display = "initial";

}

function getInput(){

    document.getElementById("matrixInput").style.display = "none";

    for(let i = 0; i < matrixRows; i++){
    
    	for(let j = 0; j < matrixColumns; j++){
    
    		matrix[i][j] = document.getElementById('' + i + j + '').value;
    
    	}
    
    }
        
    document.getElementById("matrixCalculation").style.display = "initial";

    updateMatrix();
}

function calculate2x2(matrix_input){
    
    let det = matrix_input[0][0] * matrix_input[1][1] - matrix_input[0][1] * matrix_input[1][0];

	document.getElementById("matrixCalculation").innerHTML += '<p>$\\det(A) = a_{11} \\cdot a_{22} - a_{12} \\cdot a_{21}$</p>';

	document.getElementById("matrixCalculation").innerHTML += '<p>$\\det(A) = ' + matrix_input[0][0] + ' \\cdot ' + matrix_input[1][1] + ' - ' + matrix_input[0][1] + ' \\cdot ' + matrix_input[1][0] + '$</p>';

	document.getElementById("matrixCalculation").innerHTML += '<p>$\\det(A) = ' + det + '$</p>';

    MathJax.typeset();

    return det;

}

function calculate3x3(matrix_input, name, print){

    let det = matrix_input[0][0] * matrix_input[1][1] * matrix_input[2][2] + matrix_input[0][1] * matrix_input[1][2] * matrix_input[2][0] + matrix_input[0][2] * matrix_input[1][0] * matrix_input[2][1] - (matrix_input[0][2] * matrix_input[1][1] * matrix_input[2][0] + matrix_input[0][0] * matrix_input[1][2] * matrix_input[2][1] + matrix_input[0][1] * matrix_input[1][0] * matrix_input[2][2]);
    
    if (print == 1) {

        document.getElementById("matrixCalculation").innerHTML += '<p>$\\det(' + name + ') = a_{11} \\cdot a_{22} \\cdot a_{33} + a_{12} \\cdot a_{23} \\cdot a_{31} + a_{13} \\cdot a_{21} \\cdot a_{32} - (a_{13} \\cdot a_{22} \\cdot a_{31} + a_{11} \\cdot a_{23} \\cdot a_{32} + a_{12} \\cdot a_{21} \\cdot a_{33})$</p>';

        document.getElementById("matrixCalculation").innerHTML += '<p>$\\det(' + name + ') = ' + matrix_input[0][0] + ' \\cdot ' + matrix_input[1][1] + ' \\cdot ' + matrix_input[2][2] + ' + ' + matrix_input[0][1] + ' \\cdot ' + matrix_input[1][2] + ' \\cdot ' + matrix_input[2][0] + ' + ' + matrix_input[0][2] + ' \\cdot ' + matrix_input[1][0] + ' \\cdot ' + matrix_input[2][1] + ' - (' + matrix_input[0][2] + ' \\cdot ' + matrix_input[1][1] + ' \\cdot ' + matrix_input[2][0] + ' + ' + matrix_input[0][0] + ' \\cdot ' + matrix_input[1][2] + ' \\cdot ' + matrix_input[2][1] + ' + ' + matrix_input[0][1] + ' \\cdot ' + matrix_input[1][0] + ' \\cdot ' + matrix_input[2][2] + ')$</p>';

        document.getElementById("matrixCalculation").innerHTML += '<p>$\\det(' + name + ') = ' + det + '$</p>';
    
    }

    MathJax.typeset();

    return det;

}

function calculate4x4(matrix_input){
    
    document.getElementById("matrixCalculation").innerHTML += '<p>$\\det(A) = \\sum_{j=1}^{4} (-1)^{1+j} a_{1j} \\cdot \\det(M_{1j})$</p>';

    document.getElementById("matrixCalculation").innerHTML += '<p>$\\det(A) = (-1)^{1} \\cdot a_{11} \\cdot \\det(M_{11}) + (-1)^{2} \\cdot a_{12} \\cdot \\det(M_{12}) + (-1)^{3} \\cdot a_{13} \\cdot \\det(M_{13}) + (-1)^{4} \\cdot a_{14} \\cdot \\det(M_{14})$</p>';

    let det_array = new Array(4);
    let det = 0;
    
    let sum_string = '<p>$\\det(A) = ';
    let mult_sum_string = '<p>$\\det(A) = ';

    for (let j = 0; j < 4; j++) {
        
        let minor = new Array(3).fill().map(() => new Array(3));
        let minorRow = 0;
        let minorColumn = 0;

        for (let i = 1; i < 4; i++) {
        
            for (let k = 0; k < 4; k++) {
                    
                if (k == j) continue;

                minor[minorRow][minorColumn] = matrix_input[i][k];
                minorColumn++;
            
            }

            minorRow++;
            minorColumn = 0;
            
        }
    
        det_array[j] = Math.pow(-1, j) * matrix_input[0][j] * calculate3x3(minor, 'M_{1' + (j + 1) + '}', 1);
        det += det_array[j];
        
        if (j > 0) {

            mult_sum_string += ' + ';

        }

        mult_sum_string += '(' + Math.pow(-1, j) + ' \\cdot ' + matrix_input[0][j] + ' \\cdot ' + calculate3x3(minor, 'M_{1' + (j + 1) + '}', 0) + ')';

        if (j > 0) {

            sum_string += ' + ';

        }

        sum_string += '' + det_array[j] + '';

    }
    
    mult_sum_string += '$</p>';
    sum_string += '$</p>';

    document.getElementById("matrixCalculation").innerHTML += mult_sum_string;

    document.getElementById("matrixCalculation").innerHTML += sum_string;

    document.getElementById("matrixCalculation").innerHTML += '<p>$\\det(A) = ' + det + '$</p>';

    MathJax.typeset();

}

function calculate(){
    
    document.getElementById("calculationButton").style.display = "none";

    switch (matrixRows) {
    
        case 2:

            calculate2x2(matrix);
            break;

        case 3:

            calculate3x3(matrix, 'A', 1);
            break;

        case 4:

            calculate4x4(matrix);
            break;

    }

}
