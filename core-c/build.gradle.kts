plugins {
    `cpp-library`
}

library {
    source {
        from("src/c")
    }

    publicHeaders {
        from("src/headers")
    }
    // Set the target operating system and architecture for this library
    //targetMachines.add(machines.windows.x86_64)
}
