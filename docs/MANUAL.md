# Cipr Language Manual

## 1. Syntax Basics

### Variables
Cipr is dynamically typed. Use `let` to declare variables.
```js
let x = 10;
let name = "Creed";
let active = true;
```

### Control Flow
You can use curly braces `{}` for blocks, or omit them for single statements.

**Brace-less Style:**
```js
if (x > 5) echo "Big";
```

**Block Style:**
```js
if (x > 5) {
    echo "Big";
    echo "Huge";
}
```

#### If / Else
```js
if (condition)
    do_something();
else
    do_something_else();
```

#### Loops
```js
while (running)
    update();

for (let i = 0; i < 10; i = i + 1)
    echo i;
```

### Functions
Functions **must** use braces `{}`.
```js
fn greet(name) {
    return "Hello " + name;
}
```

## 2. Shell Features

### Environment Variables
You can access environment variables using the `$` prefix.
This is syntactic sugar for `env("VAR_NAME")`.

```js
echo $HOME;   // Prints /home/user
echo $PATH;
```

### Strings
Cipr supports both double `"` and single `'` quotes.
```js
let json = '{ "key": "value" }';
let html = "<div class='main'>";
```

## 3. API Reference

### Error Handling Policy
Cipr does not use exceptions. Check return values to handle errors:
*   **Networking**: Raw socket functions return `-1`.
*   **HTTP/System**: Most high-level functions return `null` on failure.
*   **Booleans**: Functions like `kill` and `write_file` return `false` on failure.

---

### System
*   `ls(path)`: Returns **Array** of filenames. Returns **null** on error.
*   `ps()`: Returns **Array** of running processes. Returns **null** on error.
*   `kill(pid)`: Sends SIGTERM. Returns **Boolean** (true if successful).
*   `env(name)`: Returns **String** value. Returns **null** if not set.
*   `run(cmd)`: Executes shell command. Returns **String** (stdout) or Error String.
*   `cd(path)`: Changes directory. Returns **Boolean**.
*   `cwd()`: Returns **String** (current path). Returns **null** on error.

### Networking
*   `http_get(url)`: Performs GET. Returns **String** (body). Returns **null** on error.
*   `http_post(url, body)`: Performs POST. Returns **String** (body). Returns **null** on error.
*   `listen(port)`: Opens server. Returns **Number** (FD). Returns **-1** on error.
*   `accept(server_fd)`: Blocks for client. Returns **Number** (FD). Returns **-1** on error.
*   `connect(host, port)`: Connects to host. Returns **Number** (FD). Returns **-1** on error.
*   `send(fd, data)`: Sends string. Returns **Number** (bytes sent) or **-1**.
*   `recv(fd, size)`: Receives string. Returns **String** or **null** on disconnect.
*   `close(fd)`: Closes socket. Returns **Boolean**.

### File I/O
*   `read_file(path)`: Returns **String** content or Error String.
*   `write_file(path, content)`: Writes string. Returns **Boolean**.
*   `include(path)`: Executes script. Returns **Boolean**.
*   `save_lib(name, code)`: Saves code to `~/.cipr/libs/`.

### Data Processing
*   `extract(source, start, end)`: Returns **String** substring. Returns **null** if markers not found.
*   `split(str, delimiter)`: Returns **Array** of strings.
*   `trim(str)`: Removes whitespace. Returns **String**.
*   `hex(str)`: Converts to Hex. Returns **String**.
*   `base64_encode(str)`: Encodes. Returns **String**.
*   `base64_decode(str)`: Decodes. Returns **String**.
*   `size(obj)`: Returns **Number** (length of Array or String).

### Utilities
*   `rand(max)`: Returns **Number** (0 to max-1).
*   `sleep(ms)`: Pauses execution. Returns **null**.
*   `time()`: Returns **Number** (Unix timestamp).
*   `exit(code)`: Terminates the process immediately.