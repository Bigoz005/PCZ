//zad 4

//usunięcia pola phone każdemu klientowi
db.customers.updateMany({}, { $unset: { phone: "" } });

//usunięcia pola email dla klientów którzy go nie mieli
db.customers.updateMany({ address: { $size: 0 }, { $unset: { address: "" } }); 

// To add each element of the value separately, use the $each modifier with $push
// dodanie nowego znajomego i modyfikacja istniejącego klienta z okreslonym id
db.customers.findOneAndUpdate(
  { "_id": "60be7cddc196258f06af5a4f"},
  {
    $push: {
      friends: {
        $each: [
          {
            id: 0,
            name: "Modif Mod",
          },
          {
            id: 4,
            name: "Nowy znajomy",
          },
        ],
      },
    },
  }
);

//Dodanie adresu osobom bez adresu
db.customers.updateMany(
  { address: {$size: 0},
  {
    $push: {
      address: {
            country: "New Country",
            city: "New city",
			street: "New street",
			number: 8,
          },
        ],
      },
    },
  }
);


//Dodanie promocyjnej plyty do pc przy wypozyczeniu 5 gier i jeśli jej nie ma
db.borrows.updateMany(
  {
    $and: [
      { borrowedGames: { $size: 5 } },
      {
        borrowedGames: {
          $not: {
            $elemMatch: {
              game: {
                price: 0,
                name: "promo disc",
				platform: "pc",
              },
            },
          },
        },
      },
    ],
  },
  {
    $push: {
      borrowedGames: {
        game: {
          price: 0,
          name: "promo disc",
		  platform: "pc",
        },
      },
    },
  }
);

//dodanie plyty promocyjnej przy wypozyczeniu gry drozszej niz 99.99
db.borrows.updateMany(
  {
    borrowedGames: {
      $elemMatch: { "game.price": { $gte: 100 }},
    },
  },
  {
    $push: {
      borrowedGames: {
        game: {
          price: 0,
          name: "promo disc",
		  platform: "pc",
        },
      },
    },
  }
);