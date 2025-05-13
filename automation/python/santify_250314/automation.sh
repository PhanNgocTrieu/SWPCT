# mount permisison
mount="mount -o remount,rw /"

# move folder into container
# move_folder="mv ../santify /log_data/webos1/"
# eval "$move_folder"

# Wait for 5 seconds
sleep 5

# Change to container webos
webos1="lxc-attach -n webos1"
eval "$webos1"

# Change environment
setup_env="luna-send -n 1 -f luna://com.webos.service.sdx/setServer '{\"serverIndex\":\"QA2\"}'"
eval "$setup_env"
