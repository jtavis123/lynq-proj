idf_component_register(
    SRCS "HubCloudTransport.cpp"
    INCLUDE_DIRS "include"
    REQUIRES lynq_sdk esp_event esp_netif
)
