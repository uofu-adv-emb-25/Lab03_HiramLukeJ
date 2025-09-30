# Lab 3
Status Badge: ![Lab 3 Status](https://github.com/uofu-adv-emb-25/Lab03_HiramLukeJ/actions/workflows/main.yml/badge.svg)

Written by Hiram Perez and Luke Jones

Deadlock methods were added to deadlock.c.

The test methods for threaded code are `testTimeout` and `testSuccess`.

The deadlock tests are `testDeadlock`, `testOrphanedLock` and `testFixedOrphanedLock`. Killing the task for testFixedOrphanedLock is more complicated because it forces the task into a known state to make sure it is deleted cleanly.