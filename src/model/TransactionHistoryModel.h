// SPDX-License-Identifier: BSD-3-Clause
// SPDX-FileCopyrightText: 2020-2023 The Monero Project

#ifndef TRANSACTIONHISTORYMODEL_H
#define TRANSACTIONHISTORYMODEL_H

#include <QAbstractListModel>
#include <QIcon>

class TransactionHistory;
class TransactionInfo;

/**
 * @brief The TransactionHistoryModel class - read-only table model for Transaction History
 */

class TransactionHistoryModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(TransactionHistory * transactionHistory READ transactionHistory WRITE setTransactionHistory NOTIFY transactionHistoryChanged)

public:
    enum Column
    {
        Date = 0,
        TxID,
        Description,
        Amount,
        FiatAmount,
        Balance,
        COUNT
    };

    explicit TransactionHistoryModel(QObject * parent = nullptr);
    void setTransactionHistory(TransactionHistory * th);
    TransactionHistory * transactionHistory() const;
    TransactionInfo* entryFromIndex(const QModelIndex& index) const;

    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

signals:
    void transactionHistoryChanged();

private:
    QVariant parseTransactionInfo(const TransactionInfo &tInfo, int row, int column, int role) const;
    QString formatAmount(quint64 amount) const;

    TransactionHistory * m_transactionHistory;
};

#endif // TRANSACTIONHISTORYMODEL_H
