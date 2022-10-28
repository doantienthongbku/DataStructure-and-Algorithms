#include "ConcatStringTree.h"

ConcatStringTree :: Node :: Node (const char * s) {
	// Cap nhat leftlength
	leftlenght = 0;
	// Do dai s va gan chuoi vao data
	length = 0;
	while (s[length] != '\0') length++;	// Dem do dai cua chuoi
	data = new char[length + 1];			// Do phuc tap giai thuat O(n)
	for (int i = 0; i < length; i++) data[i] = s[i]; 	// Deep copy
	data[length] = '\0';		// Ki tu ket thuc chuoi
	// Cac nhanh trai - phai
	left = nullptr;
	right = nullptr;
}


ConcatStringTree :: ConcatStringTree (const char * s) {
	this->root = new Node(s);
}

char ConcatStringTree :: get(int index) {
	if (index<0 || index>(length - 1)) throw out_of_range("Index of string is invalid!"); // Nem ra ngoai le
	while ()
	//if (index < leftlength) 
	/*CharALNode* current = this->head;						// Con tro duyet node
	for (int i = 0; i < this->ncount; i++) {				// Thuat toan chuyen index ve vi tri ki tu trong node
		if (index > current->count - 1) {					// Do phuc tap O(k) voi k la so node co trong danh sach
			index -= current->count;
			current = current->next;
		}
		else return (current->CharArrayList)[index];
	}*/
	
}
