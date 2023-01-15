function dfolder {
    local dir=$1
    if [[ -d "$dir" ]]; then
        echo "Delete $dir? [y/n]"
        read confirm
        if [[ $confirm == "y" || $confirm == "Y" ]]; then
            rm -R "$dir"
        fi
    else
        echo "$dir does not exist."
    fi
}

dfolder "$1"
