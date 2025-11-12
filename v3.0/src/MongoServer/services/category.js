const Category = require('../models/category');
const Movie = require('../services/movie');

const createCategory = async (categoryData) => {
    const { name, promoted } = categoryData;
    const category = new Category({ name, promoted });
    return await category.save();
};

const getCategoryById = async (id) => {
    const category = await Category.findById(id);
    if (!category) return null;

    return category;
};

const getAllCategories = async () => {
    return await Category.find({});
};

const updateCategory = async (id, categoryData) => {
    const { name, promoted } = categoryData;
    const category = await getCategoryById(id);
    if (!category) return null;

    if (name) category.name = name;
    if (promoted !== undefined) category.promoted = promoted;

    await category.save();
    return category;
};

// Delete category and remove it from all movies that it is in their genres
const deleteCategory = async (id) => {
    const category = await getCategoryById(id);
    if (!category) return null;

    // Fetch movies with the genre that matches category name
    const { movieCount, movieList } = await Movie.findMovieBasedOnKey({ genres: category.name });

    if (movieCount > 0) {
        for (const movie of movieList) {
            //console.log(`Updating movie with _id: ${movie._id}`);

            const originalMovie = await Movie.getMovieById(movie._id);
           // console.log('Original genres before update:', originalMovie.genres);

            //console.log('Deleting category:', category.name);

            // filter out the genre from the genres array
            const updatedGenres = originalMovie.genres.filter(genre => {
                return genre.trim() !== category.name.trim();
            });

           // console.log('Updated genres after filter:', updatedGenres);

            // Update the movie by setting the new genres array
            const updatedMovie = await Movie.updateMovie(
                movie._id,
                { genres: updatedGenres }  // Only update the genres array
            );

            //console.log('Updated movie genres:', updatedMovie.genres);
        }
    }

    // Delete the category after updating movies
    await category.deleteOne();

    return category;
};

const getAllPromotedCategories = async () => {
    const category = await Category.find({ promoted: true });
    if (!category) return null;
    return category;
};

module.exports = { 
    createCategory,
    getAllCategories, 
    getCategoryById, 
    updateCategory, 
    deleteCategory, 
    getAllPromotedCategories 
};
