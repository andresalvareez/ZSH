#!/bin/bash

function restart() {
    echo "Restart [y/n]?"
    read -r confirm
    if [[ $confirm == "y" || $confirm == "Y" ]]; then
        echo "Restarting"
        sleep 1
        sudo shutdown -r now
    else
        echo "Ok"
    fi
}

restart 
