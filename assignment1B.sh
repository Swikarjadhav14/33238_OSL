#!/bin/bash

create() {
    echo -e "\n--- Create Address Book ---"
    echo -n "Enter name of address book : "
    read record
    record="${record}.txt"
    if [ ! -f "$record" ]; then   # checks if the file exists and is a regular file
        touch "$record"		  # creates a file							
        echo "Address book $record created."
    else
        echo "Address book $record already exists."
    fi
}

insert() {
    echo -e "\n--- Insert New Record ---"
    
    while true; do
        echo -n "Enter ID: "
        read id
        if grep -q "^$id " "$record"; then   # search for id , ^ indicates start of line 
                                             # -q only check no print
            echo "ID already exists. Please enter a unique ID."
        else
            break
        fi
    done
    
    echo -n "Enter Name: "
    read name
    
    while true; do
        echo -n "Enter Phone Number (10 digits): "
        read phone
        if [[ ! "$phone" =~ ^[0-9]{10}$ ]]; then
            echo "Phone number must be exactly 10 digits. Please try again."
        else
            break
        fi
    done
    
    while true; do
        echo -n "Enter Email: "
        read email
        if [[ ! "$email" =~ ^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$ ]]; then
            echo "Invalid email format. Please try again."
        else
            break
        fi
    done
    
    echo -n "Enter Address: "                # in the same line
    read address
    
    echo "$id $name $phone $email $address" >> "$record"   # writing in file
    echo "Record added."
}

display() {
    echo -e "\n--- Address Book Records ---"
    if [ -f "$record" ]; then
        cat "$record"                       # outputs the contents of file
    else
        echo "Address book does not exist."
    fi
}

delete() {
    echo -e "\n--- Delete Record ---"
    echo -n "Enter the ID to delete: "
    read id
    if grep -q "^$id " "$record"; then
        sed -i "/^$id /d" "$record"          # deletes the line containing id 
        				     # -i makes changes to original file , not just view
        echo "Record deleted."
    else
        echo "Record not found."
    fi
}

update() {

    echo -n "Enter the ID to update: "
    read id
    
    if ! grep -q "^$id " "$record"; then
        echo "Record with ID $id not found."
        return
    fi
    
    record_line=$(grep "^$id " "$record")
    old_name=$(echo "$record_line" | awk '{print $2}')   # second occurence of string sep by spaces
    old_phone=$(echo "$record_line" | awk '{print $3}')
    old_email=$(echo "$record_line" | awk '{print $4}')
    old_address=$(echo "$record_line" | awk '{print $5}')
    
    update_mobile() {
        echo -n "Enter new mobile number: "
        read newmob
        sed -i "s/$old_phone/$newmob/" "$record"
    }

    update_name() {
        echo -n "Enter new name: "
        read newname
        sed -i "s/$old_name/$newname/" "$record"
    }

    update_email() {
        echo -n "Enter new email: "
        read newemail
        sed -i "s/$old_email/$newemail/" "$record"
    }

    update_address() {
        echo -n "Enter new address: "
        read newaddress
        sed -i "s/$old_address/$newaddress/" "$record"
    }

    while true; do
        echo -e "\n--- Update Record ---"
        echo "1) Update mobile"
        echo "2) Update name"
        echo "3) Update email"
        echo "4) Update address"
        echo "5) Exit"
        echo -n "Enter a choice: "
        read choice

        case $choice in
            1) update_mobile ;;
            2) update_name ;;
            3) update_email ;;
            4) update_address ;;
            5) break ;;
            *) echo "Invalid choice. Please try again." ;;
        esac
    done
}

sort_() {
    if [ -f "$record" ]; then
        sort -o "$record" "$record"
        echo "Records sorted by ID."
    else
        echo "Address book does not exist."
    fi
}

while true; do
    echo -e "\n--- Address Book Menu ---"
    echo "1) Create address book"
    echo "2) Insert record"
    echo "3) Display record"
    echo "4) Delete record"
    echo "5) Update record"
    echo "6) Sort records"
    echo "7) Exit"
    echo -n "Enter a choice: "
    read choice

    case $choice in
        1) create ;;
        2) insert ;;
        3) display ;;
        4) delete ;;
        5) update ;;
        6) sort_ ;;
        7) break ;;
        *) echo "Invalid choice. Please try again." ;;
    esac
done

