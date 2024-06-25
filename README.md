# IwString

A custom string type created only for the purpose of learning. Most sane people use `std::string`.

## To Do

- Fix memory leaks
- Refactoring/clean up
- Although not noticable through the tests (yet), `\0` character can be added more than once, this is not intended (but happens due to the combination of using `setData()` and `append()` - two functions which need rework)
