#include <cs50.h>
#include <stdio.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_cycle(int loser, int winner);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);


            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Iterate through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If name matches
        if (!strcasecmp(name, candidates[i]))
        {
            // Update their ranks preference 0 for 1st, 1 for 2nd, and so on
            ranks[rank] = i;

            // Return true
            return true;
        }

    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

    // Update preferences array to add the current voter's preferences
    // Iterate through [i][j]
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Create variable for indexing pair
    int n = 0;

    // Iterate through one candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Iterate through second candidate
        for (int j = 0; j < candidate_count; j++)
        {
            // Check if any voter considers one candidate over the other
            if (preferences[i][j] > preferences[j][i])
            {
                // Assign winner and loser to pairs[]
                pairs[n].winner = i;
                pairs[n].loser = j;

                pair_count++;
                n++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory, largest first, smaller later
void sort_pairs(void)
{
    // Initialise pair temporary;
    pair temporary;

    // Iterate through pairs n times
    for (int i = 0; i < pair_count; i++)
    {
        // Iterate through pairs
        for (int j = 0; j < pair_count - 1; j++)
        {
            // If strength pairs[i] < strength pairs[i + 1]
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                temporary = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temporary;
            }
        }
    }

    return;
}

// Check cycles in graph
bool check_cycle(int loser, int winner)
{
    // Base case for recursive, there is a cycle because a candidate is paired with themselves
    if (loser == winner)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        // Check if there is a connection (true) between the loser and the current candidate i
        if (locked[loser][i])
        {
            // Recursively call cycle_pairs function with i as the new loser while winner is the same
            if (check_cycle(i, winner))
            {
                return true;
            }
        }
    }

    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Loop through candidates
    for (int i = 0; i < pair_count; i++)
    {
        // For each pair check if it creates a cycle
        if (!check_cycle(pairs[i].loser, pairs[i].winner))
        {
            // If it does not, update locked
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Initialise array for all candidates with an edge pointed at them
    int candidates_pointed[candidate_count];

    // Iterate through locked
    for (int i = 0, n = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // If locked is true
            if (locked[i][j])
            {
                // Add candidate to array of losers
                candidates_pointed[n] = j;
                n++;
            }
        }
    }

    // Create bool array to check if candidate[i] is in candidates_pointed
    bool candidate_in [candidate_count];

    for (int i = 0; i < candidate_count; i++)
    {
        candidate_in[i] = false;
    }

    // Check if one candidate is in candidates_pointed
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i == candidates_pointed[j])
            {
                candidate_in[i] = true;
                break;
            }
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidate_in[i])
        {
            // Print winner
            printf("%s\n", candidates[i]);
        }
    }

    return;
}