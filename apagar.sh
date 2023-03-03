#!/bin/bash

function turn_off() {
    echo "Turn off the system[y/n]?"
    read -r confirm
    if [[ $confirm == "y" || $confirm == "Y" ]]; then
        echo "Bye"
        sleep 1
        sudo shutdown -h now
    else
        echo "Ok"
    fi
}

turn_off 
