file(GLOB sources
        "*.cpp"
        )

target_sources(${TARGET_NAME}
        PRIVATE
        ${sources}
        )