## Handling Errors
When making HTTP requests in Go, it is essential to correctly handle both network errors and non-OK responses from the server. Proper error handling ensures your application can gracefully manage issues and provide meaningful feedback.

For the sake of simplicity, all previous lessons have assumed all our requests have resulted in successful responses (status code `200` - `299`).

### Network Errors
Network errors happen when there are problems reaching server, like DNS failures, connectivity issues, or timeouts. You can detect these errors by checking the `error` returned by the HTTP request function.

```go
res, err := http.Get("https://example.com/api/resource")
if err != nil {
    log.Printf("Network error: %v", err)
    return
}
defer res.Body.Close()
```

### Non-OK Responses
Even if the request is successful, the server may return a non-OK HTTP status code (e.g., 404 Not Found, 500 Internal Server Error). These responses need to be handled *separately* from network errors.

```go
res, err := http.Get("https://example.com/api/resource")
if err != nil {
    fmt.Println("a network error occurred")
    return
}
defer res.Body.Close()

if res.StatusCode != http.StatusOK {
    fmt.Println("status code != 200")
    return
}
```

*Note: A successful response usually has a status code of `http.StatucOK` (200), but it can be any code between `200` and `299`*.

What you should do with a non-OK response for your request depends on... you. You may choose to return an error, try the request again, or just log the error.

## Bugs vs Errors
Error handling is **not** the same as debugging. Likewise, errors are **not** the same as bugs.
- Good code with no bugs can still produce errors that are gracefully handled
- Bugs are, by definition, bits of code that aren't working is intended

### Debugging
"Debugging" a program is the process of going through your code to find where it is not behaving as expected. Debugging is a manual process performed by the developer. Sometimes developers use special software called "debugger" to help them find bugs, but often they just print statements to figure out what's going on.

Examples of debugging:
- Adding a missing parameter to a function call
- Updating a broken URL that an HTTP call was trying to reach
- Fixing a date-picker component in an app that wasn't displaying properly

### Error handling
"Error handling" is code that can handle *expected* edge cases in your program. Error handling is n automated process that we design into our production code to protect it from things like weak internet connections, bad user input, or bugs in other people's connections, bad user input, or bugs in other people's code that we have to interface with,

Examples of error handling:
- Checking `error` values and returning early or logging them
- Checking if pointers are not `nil`

### Don't use error handling to fix bugs
If your code has a <u>bug</u>, `error`'s won't help you. You need to just go find the bug and fix it.

If something out of your control can produce issues in your code. you should use error-handling logic to deal with it.

For example, there could be a prompt in Fantasy Quest for users to type in a new character name, but we don't want them to use punctuation. Validating their input and displaying an error message if something is wrong with it would be a form of "error handling".