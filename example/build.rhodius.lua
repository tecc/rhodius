-- First call should pretty much always be use
use_features("generator:template")

-- Code can come before the project definition

add_template("driver", path("driver.rht"))
print(path("driver.rht"))

-- Some things can't be put before a project definition, for example target definitions
project("orpheus")

target("bootloader")