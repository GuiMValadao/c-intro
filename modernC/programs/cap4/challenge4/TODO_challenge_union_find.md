Challenge 4 (Union-Find). The Union-Find problem deals with the representation of partitions over a base set. We will identify the elements of the base set using the numbers 0, 1, ...
and will represent partitions with a forest data structure where each element knows a “parent”
that is another element inside the same partition. Each set in such a partition is identified by a
designated element called the root of the set.
We want to perform two principal operations:
• A Find operation receives one element of the ground set and returns the root of the
corresponding set.
• A Uniona
operation receives two elements and merges the two sets to which these
elements belong into one.
Can you implement a forest data structure in an index table of base type size_t called
parent? Here, a value in the table SIZE_MAX would mean a position represents a root
of one of the trees; another number represents the position of the parent of the corresponding tree.
One of the important features of starting the implementation is an initialization function that
makes parent the singleton partition; that is, the partition where each element is the root of its
own private set.
With this index table, can you implement a Find function that, for a given index, finds the root
of its tree?
Can you implement a FindReplace function that changes all parent entries on a path to
the root (including) to a specific value?
Can you implement a FindCompress function that changes all parent entries to the root
that has been found?
Can you implement a Union function that, for two given elements, combines their trees into
one? Use FindCompress for one side and FindReplace for the other.