- How to read a float number "grade" from stdin?
	- `scanf("%f", &grade);`
	- `fscanf("%f", &grade, stdin);`
- How to get command line parameters from the program?
	- `int main(int argc, char** argv);`
- What are the stages of compiling the C program?
	- Preprocessing - Compiling - Assembling - Linking
 - How to define a string "username" in C (50 characters)?
	- `char username[50];`
- How to read a string "university" from stdin (4 characters)?
	- `fgets(university, 4, stdin) // safe, we specify buffer size`
	- `scanf("%s", university) // unsafe, may cause buffer overflow`
	- `fscanf(stdin, "%s", university) // unsafe, may cause buffer overflow`
	- `gets(university) // unsafe`

## Pointers
- Pointers
	- Special type of variable used to store the memory address of other variables. It is declared as: `<datatype>* var_name = NULL;`
	- `NULL` pointer is a reserved pointer in C and doesn't refer to any data objects.
	- Dynamic memory management functions: `malloc`, `calloc`, `realloc`, `free`
- Constants
	- We can declare constants in C using the keyword **const** as follows: `const <datatype> var_name = constant_value;`
- Pointers to constants
	- `const <datatype>* var_name;`
- Constant pointers to nonconstants
	- `<datatype>* const var_name = constant_address;`
- Constant pointers to constants
	- `const <datatype>* const var_name = constant_address;`

In brief:
- **Constant** pointer
	- Pointer value cannot be modified
	- Value pointed by the pointer can be modified
- Pointer to **constant**
	- Pointer value can be modified
	- Value pointed by the pointer cannot be modified
- **Constant** pointer to **constant**
	- Pointer value cannot be modified 
	- Value pointed by the pointer cannot be modified

Can we modify the constants in C language?
- *A const pointer in C* is a shallow read-only reference that means marking a variable at const in C protects the variable, not the object the variable refers to, from being mutated.
- Const in C is intended to create immutable but it does not provide such guarantee, and the ANSI/ISO standard states that modifying const variables through pointer will trigger ***Undefined Behavior***. Be careful!!! This means, it leaves the program unpredictable in terms of the expected results. This is a loophole. There is a stronger version of constness that might guarantee immutability. The qualifier is called *immutable* and is is available in the D programming language.
- Most C experts encourage to use const since it provides type checking benefits at compile time but you should be aware of this loophole and avoid using constants if you cannot manage them since modifying constant objects may happen non-intentionally.

## Arrays
- A contiguous collection of homogeneous elements that can be accessed using an index.
	- **Contiguous:** the elements of the array are adjacent to one another in memory with no gaps between them.
	- **Homogeneous:** all of the elements are of the same data type.
	- Has a fixed size. `sizeof(arr)/sizeof(arr[0]);`
	- Can be in multiple dimensions (2d, 3d, ...etc)
- **Dynamic** array: a variable size array which allows to modify its size after creating by the support of the pointers' `realloc` functionality.

## Structures
Contains a number of different data types grouped together.
Declared as:

```c
struct structure_name {
	...
	fields;
	...
} var1, var2;
```

Example: `struct Person {char* name; int age; float height;} p1;`
- Structure fields can be accessed through a structure variable using a dot (.) operator. (e.g. `p1.age`)
- Structure elements can be accessed through a pointer to a structure using the arrow (`->`) operator. (e.g. `(&p1)->age`)
- All elements of one structure variable can be assigned to another structure variable using assignment (=) operator. `struct Person p2 = p1;`

## Function pointers
**Function pointer:**
- A pointer that holds the address of a function. Declared as: `<return type> (*func_name)(types);`
- Examples:
	- `double (*f1)(int);`
	- `int* (*f2)(char*);`
**Variadic function:**
- A function which accepts a variable number of arguments. Declared as: `<return type> func_name(first_params, ...)`
- The parameter list ends with ellipsis (...)
- Examples: `int sum(int n1, ...);`

```c
int variadic_addition(int count, ...) {
	va_list args;
	int i, sum;

	va_start (args, count);

	sum = 0;
	for (i = 0; i < count; i++) {
		sum += va_arg(args, int); // get the next argumet value
	}

	va_end(args);
	return sum;
}
```

