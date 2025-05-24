function changeMethod(){
	
	const options = ['option1', 'option2', 'option3'];
	const methods = ['karty', 'akordeon', 'karuzela'];

	methods.forEach((methodID, index) => {
		
		const section = document.getElementById(methodID);
			
		if (document.getElementById(options[index]).checked){
				
			section.style.display = 'block';
			  
		} 
		else{
				
			section.style.display = 'none';
			  
		}
			
	});
	
}

document.addEventListener('DOMContentLoaded', function(){

	document.querySelectorAll('input[name="options"]').forEach((input) => {
		
		input.addEventListener('change', changeMethod);
		
	});

  changeMethod();
  
});