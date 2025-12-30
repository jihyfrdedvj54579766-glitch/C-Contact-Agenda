# Contact Agenda (C)

A simple contact management program written in C. This project is designed as an introductory exercise to practice structures, arrays, pointers, input handling, and modular programming in C.

## Features

- Add a new contact (Name, Phone, Email)
- Display all saved contacts
- Delete a contact by its index
- Simple console-based menu system

## Getting Started

This project is self-contained and does not require any external libraries.

### Compilation

To compile the program, use `gcc` or any C compiler:

```c
gcc contactAgenda.c -o contactAgenda
```

## Usage

Run the compiled program:

```c
./agenda
```

You will see a menu like this:

```c
----- Contact Agenda Menu -----
1. Show all Contacts
2. Add a Contact
3. Delete a Contact
4. Exit
Choose an option:
```
Just follow the prompts to manage your contacts.

## Code Structure

- main() — Main loop and user interaction
- addContact() — Adds a new contact
- showContacts() — Displays all stored contacts
- deleteContact() — Deletes a contact by number
- clearInputBuffer() — Helper function to flush input buffer

## Contributing

Pull requests are welcome! If you'd like to suggest improvements or add new features, feel free to open an issue to start a discussion.

If you’re learning C too, feel free to fork this and modify it for your own practice.

## License

[MIT](https://choosealicense.com/licenses/mit/)
