const mongoose = require('mongoose');
const Trip = require('../models/travlr'); // Register model
const { route } = require('../routes');
const Model = mongoose.model('trips');

// GET: /trips - list all trips
// Regardless of outcome, response must include HTML status code
// and JSON message to the requesting client 
const tripsList = async(req, res) => {
    const q = await Model
        .find({}) // No filter, return all records
        .exec();

        // Uncomment the following line to show the results of query
        // on the consol
        //consol.log(q);

    if (!q) {
        // Database returned no data
        return res
                .status(404)
                .json(err);
    } else { // Return resulting trip list
        return res
            .status(202)
            .json(q);
    }

};
// GET: /trips/:tripCode - list a single trip
// Regardless of outcome, response must include HTML status code
// and JSON message to the requesting client 
const tripsFindByCode = async(req, res) => {
    const q = await Model
        .find({'code' : req.params.tripCode}) // Return single record
        .exec();

        // Uncomment the following line to show the results of query
        // on the consol
        //consol.log(q);
    if (!q) {
        // Database returned no data
        return res
                .status(404)
                .json(err);
    } else { // Return resulting trip list
        return res
            .status(202)
            .json(q);
    }
        
};

module.exports = {
    tripsList,
    tripsFindByCode
};

