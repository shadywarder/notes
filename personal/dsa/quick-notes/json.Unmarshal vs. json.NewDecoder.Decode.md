It really depends on what your input is. If you look at the implementation of the `Decode` method of `json.Decoder`, it buffers the entire JSON value in memory before unmarshalling it into a Go value. So in most cases it won't be any more memory efficient (although this could easily change in a future version of the language).

So a better rule of thumb is this:

- Use `json.Decoder` if your data is coming from an `io.Reader` stream, or you need to decode multiple values from a stream of data.
- Use `json.Unmarshal` if you already have the JSON data in memory.

For the case of reading from an HTTP request, I'd pick `json.Decoder` since you're obviously reading from a stream.

Original answer: https://stackoverflow.com/questions/21197239/decoding-json-using-json-unmarshal-vs-json-newdecoder-decode