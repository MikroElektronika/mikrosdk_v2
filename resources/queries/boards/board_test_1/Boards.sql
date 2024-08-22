INSERT INTO Boards (
    uid,name,icon,default_device,soldered_device,
    category,mikrobus_count,sort_order,min_pin_count,display_socket,
    sdk_config,
    necto_config,display,package_uid
)
VALUES (
    "UNI_CLICKER","UNI Clicker","images/boards/clicker-uni.png",NULL,NULL,
    "Supporting tools",4,8,0,"NO_DISPLAY",
    '{"_MSDK_BOARD_NAME_":"UNI_CLICKER","HAS_MIKROBUS":"true"}',
    NULL,"NO_DISPLAY",NULL
);
