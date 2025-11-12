const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const Movie = new Schema({
    short_id: { type: Number, required: true, unique: true, min: 0, max: 10000 },
    title: { type: String, required: true, unique: true },
    releaseYear: { type: String },
    description: { type: String },
    age_Rating: {
        age: { type: String }, // Example: "18+", "PG-13", etc.
        description: [{ type: String }] // Example: "Death", etc.
    },
    actors: { type: Array },
    creators: { type: Array },
    genres: { type: Array },
    poster: { type: String },
    image: { type: String },
    trailer: { type: String },
    isSeries: { type: Boolean, default: false },
    duration: { type: String }
}, 
{ timestamps: true });

module.exports = mongoose.model('Movie', Movie);