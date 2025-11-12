const mongoose = require('mongoose');

const userSchema = new mongoose.Schema({
  name: { type: String, required: true },
  short_id: { type: Number, required: true, unique: true, min: 0},
  email: { type: String, required: true,unique: true },
  phone: { type: String, required: true, unique: true },
  profilePicture: { type: String, default: '' },
  username: { type: String, required: true, unique: true },
  password: { type: String, required: true },
  isAdmin: { type: Boolean, default: false },
  watchlist: {   
    type: Map,
    of: mongoose.Schema.Types.ObjectId, // Store ObjectId as the value for each short_id
    default: {}
  }
}, 
  { timestamps: true
});

module.exports = mongoose.model('User', userSchema);
