#ifndef EXCEPTION_H
#define EXCEPTION_H

/*!
 * \brief Classe des Exceptions declanchees dans l'application
 */
class CalendarException{
public:
    /*!
     * \brief Constructeur
     * \param message : Message correspondant a l'erreur declanchee
     */
    CalendarException(const QString& message):info(message){}

    /*!
     * \brief Permet d'avoir des informations sur l'erreur declanchee
     * \return message de l'erreur
     */
    QString getInfo() const { return info; }
private:
    QString info;
};

#endif // EXCEPTION_H

