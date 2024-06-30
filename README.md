# IwString

A custom string type created only for the purpose of learning. Most sane people use `std::string`.

## To Do

- Fix memory leaks
- Refactoring/clean up
- Although not noticable through the tests (yet), `\0` character can be added more than once, this is not intended (but happens due to the combination of using `setData()` and `append()` - two functions which need rework)
- Comment the code to clear up how I've implemented certain algorithms
- Use the Boyer–Moore algorithm for the `find()` method instead of brute force
    - If the length of `findStr` is one character, use a single for-loop

## License

IwString is released under the MIT license ([more details](./LICENSE))
