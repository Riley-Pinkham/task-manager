

CREATE TABLE IF NOT EXISTS Task (
    id INTEGER PRIMARY KEY,
    title TEXT NOT NULL UNIQUE,
    description TEXT,
    priority TEXT,
    assignee TEXT
    -- The below may need to be added back... Not sure yet
    -- column_id INTEGER,
    -- FOREIGN KEY(column_id) REFERENCES Column(id)
);
CREATE TABLE IF NOT EXISTS Column (
    id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    task_count INTEGER DEFAULT 0,
    board_id INTEGER,
    FOREIGN KEY(board_id) REFERENCES Board(id)

);
CREATE TABLE IF NOT EXISTS Board (
    id INTEGER PRIMARY KEY,
    name TEXT NOT NULL
);