# 42cursus - philosophers v.7

![](https://img.shields.io/badge/eval-100%25-brightgreen)
![](https://img.shields.io/badge/norminette%202.0.0-passing-brightgreen)

## Project Information

### About

> In this project, you will learn the basics of threading a process. You will
learn how to make threads. You will discover the mutex and the semaphore.

This project is about optimisation to save the most CPU usage possible to ensure the survival of all our philosophers.

**philo_one**: only multi-threads and mutex allowed
**philo_two**: only multi-threads and semaphore allowed
**philo_three**: only multi-processes and semaphore allowed

### Mandatory

The program should take the following arguments: `number_of_philosophers` `time_to_die`
`time_to_eat` `time_to_sleep` `[number_of_times_each_philosopher_must_eat]`
- number_of_philosophers: is the number of philosophers and also the number
of forks.
- time_to_die: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’
milliseconds after starting their last meal or the beginning of the simulation,
it dies.
- time_to_eat: is in milliseconds and is the time it takes for a philosopher to
eat. During that time they will need to keep the two forks.
- time_to_sleep: is in milliseconds and is the time the philosopher will spend
sleeping.
- number_of_times_each_philosopher_must_eat: argument is optional, if all
philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the
simulation will stop. If not specified, the simulation will stop only at the death
of a philosopher.
