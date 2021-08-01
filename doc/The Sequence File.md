
# The Sequence File

The `assets/sequence.txt` file is used to make the game's map.  
The file has the following structure:  

```text
<number of sequences>

<start> <end> <total height> <number of entities>
<x> <y> <type>
<x> <y> <type>
…

<start> <end> <total height> <number of entities>
<x> <y> <type>
<x> <y> <type>
…
```

The first line indicates the number of sequences that are in the file.  
For each sequence, the first line has it's info:  
  
`<start>`: Start point score. The minimum score (doodle's current height) needed for this sequence to appear in the map.  
`<end>`: End point score. The maximum score that the sequence will appear in. Set to -1 if there is no limit.  
`<total height>`: The height of the sequence.  
`<number of entities>`: The number of entities in the sequence.  
  
After the info line, we list the entities inside the sequence: (The total should be `<number of entities>`)  
  
`<x>`: The entity's middle-bottom point's x.  
(The coordinates are measured from the bottom-left corner of the screen)  
(Keep in mind that the screen's width is 400px)  
`<y>`: The entity's middle-bottom point's y.  
`<type>`: The entity's type, which is one of the following:
  
| Game Object        | Type      |
| ------------------ | --------- |
| Normal Platform    | platform  |
| Moving Platform    | mplatform |
| Breakable Platform | bplatform |
| Spring             | spring    |
| Normal Enemy       | enemy     |
