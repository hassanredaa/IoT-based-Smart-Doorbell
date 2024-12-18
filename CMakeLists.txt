add_executable(${ProjectName}
    main.c
    led.c
    lcd.c
    light_sensor.c
    motion_sensor.c
    buzzer.c
    button.c
)

target_include_directories(${ProjectName} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${ProjectName} 
    pico_stdlib 
    FreeRTOS-Kernel-Heap4 
    )

    target_link_libraries(${PROJECT_NAME}
    hardware_pwm
    hardware_adc
)
pico_add_extra_outputs(${ProjectName})