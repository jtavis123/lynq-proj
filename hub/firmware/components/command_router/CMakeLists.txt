idf_component_register(
    SRCS "HubCommandRouter.cpp"
    INCLUDE_DIRS "include"
    REQUIRES lynq_sdk cloud_transport node_transport
)
