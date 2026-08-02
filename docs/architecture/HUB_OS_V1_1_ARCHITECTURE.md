# Hub OS v1.1 Architecture

Hub OS separates portable product behavior from the Waveshare board-support package.

Boot order: hardware -> storage -> display -> touch -> network -> services -> UI.
Required failures stop boot and enter diagnostics; optional network failure permits local degraded operation.

Primary pages: Home, Devices, Rooms, Scenes, Learn, Settings. Diagnostics and Factory Mode remain under Settings.
