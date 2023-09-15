#include <cs50.h>
#include <stdio.h>
#include <strings.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Linear Search
    for (int i = 0; i < candidate_count; i++)
    {
        // If name == valid candidate
        if (!strcasecmp(name, candidates[i].name))
        {
            // Update preferences array with voter and rank preference
            // 0 == 1st preference, 1 == 2nd preference, and so on
            preferences[voter][rank] = i;
            return true;
        }
    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Each voter votes for their top-preffered candidate
    for (int i = 0; i < voter_count; i++)
    {
        // Loop through each rank
        for (int j = 0; j < candidate_count; j++)
        {
            // Update votes if top ranked not eliminated
            if (!candidates[preferences[i][j]].eliminated)
            {
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Linear Search
    for (int i = 0; i < candidate_count; i++)
    {
        // If candidate > half of the votes, winner
        if (candidates[i].votes > (voter_count / 2))
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Declare variable for min with voter_count (max number)
    int min = voter_count;

    // Iterate through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If min is greater than the number of votes for a candidate
        if (min > candidates[i].votes && !candidates[i].eliminated)
        {
            // Assign minimum votes
            min = candidates[i].votes;
        }
    }

    // Return minimum number of votes
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Iterate through candidates
    for (int i = 0; i < candidate_count - 1; i++)
    {
        // If all candidates not eliminated votes != min
        if (candidates[i].votes != min && !candidates[i].eliminated)
        {
            return false;
        }
    }

    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Iterate through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If candidates not eliminated == min
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }

    return;
}