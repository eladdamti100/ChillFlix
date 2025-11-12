const User = require("../models/user");

// Create a new user
const createUser = async (userData) => {
  try {
    const user = new User(userData);
    return await user.save();
  } catch (error) {
    if (error.code === 11000) {
      throw new Error("Username or email or short_id already exists");
    }
    throw error;
  }
};

// Find user by username
const findUserByUsername = async (username) => {
  return await User.findOne({ username });
};

// Find user by username and password
const findUserByUsernameAndPassword = async (username, password) => {
  return await User.findOne({ username, password });
};

// Get user by ID
const getUserById = async (id) => {
  const user = await User.findById(id);
  if (!user) throw new Error("User not found");
  return user;
};

// Get all users
const getAllUsers = async () => {
  return await User.find();
};

// Update user details
const updateUserDetails = async (id, updates) => {
  try {
    const user = await User.findById(id);
    if (!user) {
      throw new Error("User not found");
    }

    Object.keys(updates).forEach((key) => {
      user[key] = updates[key];
    });

    await user.save();
    return user;
  } catch (error) {
    if (error.code === 11000) {
      throw new Error("Username or email already exists");
    }
    throw new Error("An error occurred while updating user details");
  }
};

/* Delete user
const deleteUser = async (id) => {
  try {
    const user = await User.findByIdAndDelete(id);
    if (!user) {
      throw new Error("User not found");
    }
    return user;
  } catch (error) {
    throw new Error("An error occurred while deleting the user");
  }
};
*/

// Add movie to user's watchlist
const addMovieToUser = async (userId, shortId, movieId) => {
  try {
    const user = await User.findByIdAndUpdate(
      userId,
      { $set: { [`watchlist.${shortId}`]: movieId } },
      { new: true }
    );
    if (!user) {
      throw new Error("User not found");
    }
    return user;
  } catch (error) {
    throw new Error("Failed to add movie to user's watchlist");
  }
};

// Remove movie from a single user's watchlist
const removeMovieFromUser = async (userId, shortId) => {
  try {
    const user = await User.findByIdAndUpdate(
      userId,
      { $unset: { [`watchlist.${shortId}`]: "" } },
      { new: true }
    );
    if (!user) {
      throw new Error("User not found");
    }
    return user;
  } catch (error) {
    throw new Error(`Failed to remove movie from user ${userId}'s watchlist`);
  }
};

// Remove movie from all users' watchlists
const removeMovieFromAllWatchlists = async (movieShortId) => {
  try {
    await User.updateMany(
      { [`watchlist.${movieShortId}`]: { $exists: true } },
      { $unset: { [`watchlist.${movieShortId}`]: "" } }
    );
    console.log(`Movie ${movieShortId} removed from all users' watchlists`);
  } catch (error) {
    throw new Error("Failed to remove movie from all users' watchlists");
  }
};

module.exports = {
  createUser,
  getAllUsers,
  getUserById,
  updateUserDetails,
//  deleteUser,
  findUserByUsername,
  findUserByUsernameAndPassword,
  addMovieToUser,
  removeMovieFromUser,
  removeMovieFromAllWatchlists,
};
