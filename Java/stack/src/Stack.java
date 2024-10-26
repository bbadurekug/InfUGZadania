public class Stack {
	private String [] elements = new String[0];
	private String [] temp = new String[0];

	//dodac try catch gdziekolwiek
	//bez maina i bez println

	private boolean isEmpty(String[] stack){

		if(stack.length == 0){ return true;}
		return false;

	}

	private void copyStack(String[] source, String[] dest) {

		if(isEmpty(source) || isEmpty(dest)){return;}

		int len = (source.length < dest.length)? source.length: dest.length;

		for(int i = 0; i < len; i++) {

			dest[i] = source[i];

		}

	}

	public void push(String element){

		this.temp = new String[this.elements.length + 1];
		copyStack(this.elements, this.temp);
		this.temp[this.temp.length - 1] = element;
		this.elements = this.temp;

	}
	public String pop(){

		if(isEmpty(this.elements)) {return "";}

		String result = this.elements[this.elements.length - 1];
		this.temp = new String[this.elements.length - 1];
		copyStack(this.elements, this.temp);
		this.elements = this.temp;
		return result;

	}

	public String peek(){

		if(isEmpty(this.elements)) {return "";}

		return this.elements[this.elements.length - 1];

	}
}
