# Angelscript-Integration

A mirror of the released versions of the [AngelScript sdk](http://angelcode.com/angelscript/).

AngelScript is licensed using a [zlib like license](http://angelcode.com/angelscript/sdk/docs/manual/doc_license.html).

> AngelCode Scripting Library
>
> Copyright © 2003-2015 Andreas Jönsson
>
> This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.
>
> Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
>
> 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
> 
> 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
>
> 3. This notice may not be removed or altered from any source distribution.

# Additional Features

Additional to mirroring Angelscript, this repository also contains some additional features:

- `init_message_callback_qt` registers a message handler logging to the qt debug streams like qDebug(), qWarning(), qCritical()
- `init_logging_functions_qt` registers explicit Angelscript functions thought for logging (also logging to the qt debug streams)
    - `void log_debug(const string &in)`
    - `void log_info(const string &in)`
    - `void log_warning(const string &in)`
    - `void log_critical(const string &in)`
- `init_glm` registers a subset of the functionality provided by glm.  
    - Based on code of a hobby-project I made years ago, the vector types and the swizzle operators are integrated.

