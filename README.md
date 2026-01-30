# Task-Tracker-Cli-Tool

https://roadmap.sh/projects/task-tracker

## Compliation
```
cmake -B build
cmake --build build
```

## Usage Example
```
./build/task-cli -h

Example usage
	 task-cli add "[ DESCRIPTION OF THE TASK ]"
	 task-cli update [ INDEX OF THE TASK ] "[ DESCRiPTION OF THE TASK ]"
	 task-cli delete [ INDEX OF THE TASK ]
	 task-cli mark-in-progress [ INDEX OF THE TASK ]
	 task-cli mark-done [ INDEX OF THE TASK ]
	 task-cli list
	 task-cli list [ SOME STATUS F.E 'todo', 'done', 'in progress' ]

./build/task-cli add "Buy groceries"
Task added successfully (ID: 1)

./build/task-cli list
❌ ❌ ❌ ❌ ❌ ❌

	• Id: 1

	• Description: Buy groceries

	• Created: Friday 30th of February at 18:54

	• Updated: Friday 30th of February at 18:54

❌ ❌ ❌ ❌ ❌ ❌
