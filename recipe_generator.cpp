#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

// --- CORE DATA STRUCTURES ---

/**
 * @brief Represents a single ingredient in the knowledge base.
 */
struct Ingredient {
    string name;
    set<string> tags; // e.g., "Vegan", "Gluten-Free", "Dairy", "Spice"
};

/**
 * @brief Represents a single recipe.
 */
struct Recipe {
    string title;
    string cuisine; // e.g., "Italian", "Indian", "Mexican"
    int timeMinutes;
    set<string> requiredIngredients; // Simplified to just names
    set<string> tags; // Overall recipe tags: "Vegan", "Fast", "Low-Calorie"
    vector<string> steps;

    void print() const {
        cout << "Recipe: " << title << "\n";
        cout << "Cuisine: " << cuisine << " | Time: " << timeMinutes << " mins\n";
        cout << "Tags: ";
        for (const auto& tag : tags) { cout << tag << " "; }
        cout << "\nIngredients needed:\n";
        for (const auto& ing : requiredIngredients) { cout << "- " << ing << "\n"; }
        cout << "\nSteps:\n";
        for (int i = 0; i < steps.size(); ++i) {
            cout << (i + 1) << ". " << steps[i] << "\n";
        }
        cout << "\n";
    }
};

// --- RECIPE GENERATION LOGIC ---

class RecipeGenerator {
private:
    vector<Recipe> recipeDatabase;

    /**
     * @brief Populates a simplified, rule-based database.
     */
    void loadDatabase() {
        // Recipe 1: Quick Vegan Salad (Fast & Vegan)
        Recipe r1;
        r1.title = "Mediterranean Quinoa Salad";
        r1.cuisine = "Mediterranean";
        r1.timeMinutes = 20;
        r1.requiredIngredients = {"Quinoa", "Cucumber", "Tomato", "Lemon", "Olive Oil"};
        r1.tags = {"Vegan", "Fast", "Gluten-Free"};
        r1.steps = {"Boil quinoa.", "Chop vegetables.", "Mix all with lemon and oil."};
        recipeDatabase.push_back(r1);

        // Recipe 2: Chicken Curry (Time-Consuming)
        Recipe r2;
        r2.title = "Spicy Chicken Curry";
        r2.cuisine = "Indian";
        r2.timeMinutes = 45;
        r2.requiredIngredients = {"Chicken", "Onion", "Ginger", "Yogurt", "Curry Powder"};
        r2.tags = {"Non-Vegetarian", "Spicy"};
        r2.steps = {"Sauté onions.", "Add chicken and spices.", "Simmer with yogurt."};
        recipeDatabase.push_back(r2);

        // Recipe 3: Pasta Dish (Fast, Non-Vegan)
        Recipe r3;
        r3.title = "Simple Creamy Pasta";
        r3.cuisine = "Italian";
        r3.timeMinutes = 25;
        r3.requiredIngredients = {"Pasta", "Cream", "Butter", "Garlic", "Parmesan"};
        r3.tags = {"Vegetarian", "Fast"};
        r3.steps = {"Boil pasta.", "Make sauce from cream/butter.", "Toss pasta in sauce."};
        recipeDatabase.push_back(r3);
    }

public:
    RecipeGenerator() {
        loadDatabase();
    }

    /**
     * @brief Generates recipes based on user constraints.
     * @param availableIngredients Ingredients the user has.
     * @param requiredTags Dietary/style tags (e.g., "Vegan").
     * @param maxTime Max cooking time in minutes.
     * @return Vector of recipes matching all constraints.
     */
    vector<Recipe> generate(
        const set<string>& availableIngredients,
        const set<string>& requiredTags,
        int maxTime) {

        vector<Recipe> results;

        for (const auto& recipe : recipeDatabase) {
            // 1. Time Constraint Check
            if (recipe.timeMinutes > maxTime) {
                continue;
            }

            // 2. Dietary/Style Tag Check (All required tags must be present)
            bool tagsMatch = true;
            for (const auto& requiredTag : requiredTags) {
                if (recipe.tags.find(requiredTag) == recipe.tags.end()) {
                    tagsMatch = false;
                    break;
                }
            }
            if (!tagsMatch) {
                continue;
            }

            // 3. Ingredient Availability Check (Simple: must have ALL required ingredients)
            bool ingredientsAvailable = true;
            for (const auto& requiredIng : recipe.requiredIngredients) {
                if (availableIngredients.find(requiredIng) == availableIngredients.end()) {
                    ingredientsAvailable = false;
                    break;
                }
            }
            if (ingredientsAvailable) {
                // All constraints passed!
                results.push_back(recipe);
            }
            // Note: A more advanced version would use a score based on ingredient match percentage
        }

        return results;
    }
};

// --- MAIN FUNCTION (User Interaction Mock-up) ---

void runRecipeGeneratorDemo() {
    RecipeGenerator generator;

    cout << "Welcome to the Interactive Recipe Generator!\n";
    cout << "------------------------------------------\n";

    // --- User Input Mock-up ---
    set<string> userIngredients = {"Quinoa", "Cucumber", "Tomato", "Lemon", "Olive Oil", "Pasta", "Garlic"};
    set<string> userTags = {"Vegan", "Fast"};
    int userMaxTime = 30;

    cout << "User Constraints:\n";
    cout << "Available Ingredients (7): Quinoa, Cucumber, Tomato, Lemon, Olive Oil, Pasta, Garlic\n";
    cout << "Required Tags: Vegan, Fast\n";
    cout << "Max Time: " << userMaxTime << " minutes\n\n";

    // 

    // --- Generation ---
    vector<Recipe> matchingRecipes = generator.generate(userIngredients, userTags, userMaxTime);

    // --- Output ---
    if (matchingRecipes.empty()) {
        cout << "Sorry, no recipes matched all your constraints.\n";
    } else {
        cout << "Found " << matchingRecipes.size() << " matching recipe(s)!\n";
        cout << "------------------------------------------\n";
        for (const auto& recipe : matchingRecipes) {
            recipe.print();
        }
    }
}

// int main() {
//     runRecipeGeneratorDemo();
//     return 0;
// }